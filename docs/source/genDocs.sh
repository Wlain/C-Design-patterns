#!/usr/bin/env bash

cd $(dirname $0)

THIS_DIR=$(pwd)
cd ../../
PROJECT_DIR=$(pwd)
cd ${THIS_DIR}

# run sphinx
SPHINX_SOURCE_DIR=$(pwd)
SPHINX_BUILD_DIR=${SPHINX_SOURCE_DIR}/generated

rm -rf ${SPHINX_BUILD_DIR}
mkdir -p ${SPHINX_BUILD_DIR}

if [[ "$(uname -s)" == 'Darwin' ]] && ! [ -x "$(command -v sphinx-build)" ]; then
    echo "sphinx-build is not installed. run "brew install sphinx-build" manully"
    if ! brew install sphinx-build; then
        echo "installing sphinx-build failed! please try it your self!"
        exit 1
    fi
fi

pip install sphinx-rtd-theme sphinx_rtd_size sphinx_markdown_tables myst_parser
cp ${PROJECT_DIR}/README.md ${THIS_DIR}
sphinx-build -b html ${SPHINX_SOURCE_DIR} ${SPHINX_BUILD_DIR}
rm ${THIS_DIR}/README.md
echo "Generating documentation with Sphinx!"
