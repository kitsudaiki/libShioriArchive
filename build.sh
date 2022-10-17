#!/bin/bash

# get current directory-path and the path of the parent-directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PARENT_DIR="$(dirname "$DIR")"

# create build-directory
BUILD_DIR="$PARENT_DIR/build"
mkdir -p $BUILD_DIR

# create directory for the final result
RESULT_DIR="$PARENT_DIR/result"
mkdir -p $RESULT_DIR

#-----------------------------------------------------------------------------------------------------------------

function build_kitsune_lib_repo () {
    REPO_NAME=$1
    NUMBER_OF_THREADS=$2
    ADDITIONAL_CONFIGS=$3

    # create build directory for repo and go into this directory
    REPO_DIR="$BUILD_DIR/$REPO_NAME"
    mkdir -p $REPO_DIR
    cd $REPO_DIR

    # build repo library with qmake
    /usr/lib/x86_64-linux-gnu/qt5/bin/qmake "$PARENT_DIR/$REPO_NAME/$REPO_NAME.pro" -spec linux-g++ "CONFIG += optimize_full staticlib $ADDITIONAL_CONFIGS"
    /usr/bin/make -j$NUMBER_OF_THREADS

    # copy build-result and include-files into the result-directory
    cp $REPO_DIR/src/$REPO_NAME.a $RESULT_DIR/
    cp -r $PARENT_DIR/$REPO_NAME/include $RESULT_DIR/
    ls -l $RESULT_DIR/include/
    ls -l $RESULT_DIR
}

function get_required_kitsune_lib_repo () {
    REPO_NAME=$1
    TAG_OR_BRANCH=$2
    NUMBER_OF_THREADS=$3
    ADDITIONAL_CONFIGS=$4

    # clone repo
    git clone  https://github.com/kitsudaiki/$REPO_NAME.git "$PARENT_DIR/$REPO_NAME"
    cd "$PARENT_DIR/$REPO_NAME"
    git checkout $TAG_OR_BRANCH

    build_kitsune_lib_repo $REPO_NAME $NUMBER_OF_THREADS $ADDITIONAL_CONFIGS
}

function download_repo_github () {
    REPO_NAME=$1
    TAG_OR_BRANCH=$2

    # clone repo
    git clone https://github.com/kitsudaiki/$REPO_NAME.git "$BUILD_DIR/$REPO_NAME"
    git clone https://github.com/kitsudaiki/$REPO_NAME.git "$PARENT_DIR/$REPO_NAME"
    cd "$BUILD_DIR/$REPO_NAME"
    git checkout $TAG_OR_BRANCH
    cd "$PARENT_DIR/$REPO_NAME"
    git checkout $TAG_OR_BRANCH
}


#-----------------------------------------------------------------------------------------------------------------
echo ""
echo "###########################################################################################################"
echo ""
get_required_kitsune_lib_repo "libKitsunemimiCommon" "v0.27.1" 8
get_required_kitsune_lib_repo "libKitsunemimiJson" "v0.12.0" 1
get_required_kitsune_lib_repo "libKitsunemimiJinja2" "v0.10.0" 1
get_required_kitsune_lib_repo "libKitsunemimiIni" "v0.6.0" 1
get_required_kitsune_lib_repo "libKitsunemimiNetwork" "v0.9.0" 8
get_required_kitsune_lib_repo "libKitsunemimiArgs" "v0.5.0" 8
get_required_kitsune_lib_repo "libKitsunemimiConfig" "v0.5.0" 8
get_required_kitsune_lib_repo "libKitsunemimiCrypto" "v0.3.0" 8
get_required_kitsune_lib_repo "libKitsunemimiJwt" "v0.5.1" 8
echo ""
echo "###########################################################################################################"
echo ""
get_required_kitsune_lib_repo "libKitsunemimiSakuraNetwork" "v0.9.0" 8
get_required_kitsune_lib_repo "libKitsunemimiSakuraLang" "v0.13.0" 1
echo ""
echo "###########################################################################################################"
echo ""
get_required_kitsune_lib_repo "libKitsunemimiHanamiCommon" "v0.3.0" 8
get_required_kitsune_lib_repo "libKitsunemimiHanamiEndpoints" "v0.2.0" 1
get_required_kitsune_lib_repo "libKitsunemimiHanamiNetwork" "v0.5.0" 8
download_repo_github "libKitsunemimiHanamiMessages" "v0.1.0"
echo ""
echo "###########################################################################################################"

#-----------------------------------------------------------------------------------------------------------------

if [ $1 = "test" ]; then
    build_kitsune_lib_repo "libShioriArchive" 8 "run_tests"
else
    build_kitsune_lib_repo "libShioriArchive" 8
fi

#-----------------------------------------------------------------------------------------------------------------

