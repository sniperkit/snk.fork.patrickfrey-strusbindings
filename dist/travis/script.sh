#!/bin/sh

set -e

OS=$(uname -s)

PROJECT=strusBindings

build_strus_project() {
	prj_cmakeflags=$1
	case $OS in
		Linux)
			mkdir build
			cd build
			cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release \
				-DLIB_INSTALL_DIR=lib -DCMAKE_CXX_FLAGS=-g $prj_cmakeflags \
				..
			make VERBOSE=1
			make VERBOSE=1 CTEST_OUTPUT_ON_FAILURE=1 test
			sudo make VERBOSE=1 install
			cd ..
			;;

		Darwin)
			# forcing brew versions (of gettext) over Mac versions
			export CFLAGS=-I/usr/local
			export CXXFLAGS=-I/usr/local
			export LDFLAGS=-L/usr/local/lib
			mkdir build
			cd build
			cmake \
				-DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release \
				-DCMAKE_CXX_FLAGS='-g -Wno-error=format-nonliteral -Wno-error=format-security' -G Xcode $prj_cmakeflags \
				..
			xcodebuild -configuration Release -target ALL_BUILD
			xcodebuild -configuration Release -target RUN_TESTS
			sudo xcodebuild -configuration Release -target install
			cd ..
			;;
			
		*)
			echo "ERROR: unknown operating system '$OS'."
			;;
	esac
}

# build pre-requisites
DEPS="strusBase strus strusAnalyzer strusTrace strusModule strusRpc strusVector"

GITURL=`git config remote.origin.url`
cd ..
for i in $DEPS; do
	git clone `echo $GITURL | sed "s@/$PROJECT\.@/$i.@g"` $i
	cd $i
	git submodule update --init --recursive
	git submodule foreach --recursive git checkout master
	git submodule foreach --recursive git pull

	build_strus_project ""
	cd ..
done

# build the package itself
cd $PROJECT
case $OS in
	Linux)
		build_strus_project "-DWITH_PHP=YES -DWITH_PYTHON=YES -DWITH_STRUS_VECTOR=YES -DWITH_STRUS_PATTERN=NO"
		;;
	Darwin)
		# Currently No Php7 on Darwin. The build succeedes, but PHP7 test SEGFAULT all, even the one that does not load strus at all
		build_strus_project "-DWITH_PHP=NO -DWITH_PYTHON=YES -DWITH_STRUS_VECTOR=YES -DWITH_STRUS_PATTERN=NO"
		;;
	*)
		echo "ERROR: unknown operating system '$OS'."
		;;
esac
cd ..


