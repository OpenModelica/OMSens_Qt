dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([OMSens_Qt],[dev],[https://trac.openmodelica.org/OpenModelica],[openmodelica],[https://openmodelica.org])

AC_SUBST(APP)
AC_SUBST(EXE)
AC_SUBST(RPATH)
AC_SUBST(RPATH_QMAKE)
AC_SUBST(host_short)

m4_include([common/m4/pre-commit.m4])
cp common/install-sh common/config.guess common/config.sub ./
m4_include([common/m4/ombuilddir.m4])
m4_include([common/m4/ax_cxx_compile_stdcxx_11.m4])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl Checks for programs.
test -z "$CXXFLAGS" && CXXFLAGS="$CFLAGS"
AC_LANG([C++])
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])

host_short=$host_cpu-$host_os

m4_include([common/m4/qmake.m4])

for flag in -Wno-clobbered; do
  OLD_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS $flag -Werror"
  AC_TRY_LINK([], [return 0;], [CXXFLAGS="$OLD_CXXFLAGS $flag"],[CXXFLAGS="$OLD_CXXFLAGS"])
done

AC_OUTPUT(Makefile.unix)

