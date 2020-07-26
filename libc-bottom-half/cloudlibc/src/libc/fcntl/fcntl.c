// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <wasi/api.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>

int fcntl(int fildes, int cmd, ...) {
  switch (cmd) {
    case F_GETFD:
      // Act as if the close-on-exec flag is always set.
      return FD_CLOEXEC;
    case F_SETFD:
      // The close-on-exec flag is ignored.
      return 0;
    case F_GETFL: {
      // Obtain the flags and the rights of the descriptor.
      __wasi_fdstat_t fds;
#ifdef __wasilibc_unmodified_upstream
      __wasi_errno_t error = __wasi_fd_stat_get(fildes, &fds);
#else
      __wasi_errno_t error = __wasi_fd_fdstat_get(fildes, &fds);
#endif
      if (error != 0) {
        errno = error;
        return -1;
      }

      // Roughly approximate the access mode by converting the rights.
      int oflags = fds.fs_flags;
      if ((fds.fs_rights_base &
#ifdef __wasilibc_unmodified_upstream
           (__WASI_RIGHT_FD_READ | __WASI_RIGHT_FILE_READDIR)) != 0) {
        if ((fds.fs_rights_base & __WASI_RIGHT_FD_WRITE) != 0)
#else
           (__WASI_RIGHTS_FD_READ | __WASI_RIGHTS_FD_READDIR)) != 0) {
        if ((fds.fs_rights_base & __WASI_RIGHTS_FD_WRITE) != 0)
#endif
          oflags |= O_RDWR;
        else
          oflags |= O_RDONLY;
#ifdef __wasilibc_unmodified_upstream
      } else if ((fds.fs_rights_base & __WASI_RIGHT_FD_WRITE) != 0) {
#else
      } else if ((fds.fs_rights_base & __WASI_RIGHTS_FD_WRITE) != 0) {
#endif
        oflags |= O_WRONLY;
#ifdef __wasilibc_unmodified_upstream
      } else if ((fds.fs_rights_base & __WASI_RIGHT_PROC_EXEC) != 0) {
        oflags |= O_EXEC;
#endif
      } else {
        oflags |= O_SEARCH;
      }
      return oflags;
    }
    case F_SETFL: {
      // Set new file descriptor flags.
      va_list ap;
      va_start(ap, cmd);
      int flags = va_arg(ap, int);
      va_end(ap);

#ifdef __wasilibc_unmodified_upstream // fstat
      __wasi_fdstat_t fds = {.fs_flags = flags & 0xfff};
      __wasi_errno_t error =
          __wasi_fd_stat_put(fildes, &fds, __WASI_FDSTAT_FLAGS);
#else
      __wasi_fdflags_t fs_flags = flags & 0xfff;
      __wasi_errno_t error =
          __wasi_fd_fdstat_set_flags(fildes, fs_flags);
#endif
      if (error != 0) {
        errno = error;
        return -1;
      }
      return 0;
    }
    case F_DUPFD: {
      int new_fd = -1;
      __wasi_errno_t error = __wasi_fd_dup(fildes, &new_fd);

      if(error != 0) {
        errno = error;
        return -1;
      }
      return new_fd;
    }
    default:
      errno = EINVAL;
      return -1;
  }
}
