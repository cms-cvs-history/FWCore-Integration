#!/bin/sh

function die { echo $1: status $2 ;  exit $2; }

cmsRun --parameter-set ${LOCAL_TEST_DIR}/context_using_example.cfg || die 'Failed in context_using_example.cfg' $?
