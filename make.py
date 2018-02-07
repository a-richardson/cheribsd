#!/usr/bin/env python3
import os
import shutil
import subprocess
import sys
from pathlib import Path

MAKEOBJDIRPREFIX = os.getenv("MAKEOBJDIRPREFIX")
source_root = Path(__file__).absolute().parent


def run(cmd, **kwargs):
    cmd = list(map(str, cmd))  # convert all Path objects to str
    print("Running", cmd)
    subprocess.check_call(cmd, **kwargs)


def bootstrap_bmake(bmake_install_dir: Path):
    bmake_source_dir = source_root / "contrib/bmake"
    bmake_build_dir = Path(MAKEOBJDIRPREFIX, "bmake-build")
    if not bmake_build_dir.exists():
        os.makedirs(str(bmake_build_dir))
    env = os.environ.copy()

    # HACK around the deleted file bmake/missing/sys/cdefs.h
    if sys.platform.startswith("linux"):
        env["CFLAGS"] = "-I /usr/include/bsd -DLIBBSD_OVERLAY"
        env["LDFLAGS"] = "-lbsd"
    configure_args = [
        "--with-default-sys-path=" + str(bmake_install_dir / "share/mk"),
        "--with-machine=amd64",  # TODO? "--with-machine-arch=amd64",
        "--without-filemon",
        "--prefix=" + str(bmake_install_dir)
    ]
    run(["sh", bmake_source_dir / "boot-strap"] + configure_args,
        cwd=str(bmake_build_dir), env=env)

    run(["sh", bmake_source_dir / "boot-strap", "op=install"] + configure_args,
        cwd=str(bmake_build_dir))


if __name__ == "__main__":
    if not MAKEOBJDIRPREFIX:
        sys.exit("MAKEOBJDIRPREFIX is not set, cannot continue!")
    if not Path(MAKEOBJDIRPREFIX).is_dir():
        sys.exit(MAKEOBJDIRPREFIX + " doesn't exit!")
    # TODO: check if the host system bmake is new enough and use that instead
    bmake_install_dir = Path(MAKEOBJDIRPREFIX, "bmake-install")
    bmake_binary = bmake_install_dir / "bin/bmake"
    if not bmake_binary.exists():
        bootstrap_bmake(bmake_install_dir)
    if not sys.platform.startswith("freebsd"):
        if not os.getenv("CC") or not os.getenv("CXX") or not os.getenv("CPP"):
            print("Crossbuilding FreeBSD from a non-FreeBSD system currently will"
                  "not work without setting CC to point to clang.")
            print("You should set CC and CXX to point to a valid clang binary")
            print("For example:")
            print("MAKEOBJDIRPREFIX=... CC=/usr/bin/clang-4.0",
                  "CXX=/usr/bin/clang++-4.0 CPP=/usr/bin/clang-cpp-4.0"
                  "./make.py buildworld")
            if sys.platform == "darwin":
                cc = "/usr/bin/clang"
                cpp = "/usr/bin/cpp"
                cxx = "/usr/bin/clang++"
            else:
                cc = shutil.which("clang") or "/usr/bin/gcc"
                cpp = shutil.which("clang-cpp") or "/usr/bin/cpp"
                cxx = shutil.which("clang++") or "/usr/bin/g++"
            os.environ.update(CC=cc, CPP=cpp, CXX=cxx, LD="/usr/bin/ld")
    os.execv(str(bmake_binary), [str(bmake_binary)] + sys.argv[1:])
