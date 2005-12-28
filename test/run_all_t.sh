#!/bin/sh


# Pass in name and status
function die { echo $1: status $2 ;  exit $2; }

${LOCAL_TEST_DIR}/refTest.sh || die 'Failed in refTest.sh' $?

${LOCAL_TEST_DIR}/inputSourceTest.sh || die 'Failed in inputSourceTest.sh' $?

${LOCAL_TEST_DIR}/eventSetupTest.sh || die 'Failed in eventSetupTest.sh' $?

${LOCAL_TEST_DIR}/context_using_example.sh || die 'Failed in context_using_example.sh' $?

${LOCAL_TEST_DIR}/hierarchy_example.sh || die 'Failed in hierarchy_example.sh' $?

${LOCAL_TEST_DIR}/service_example.sh || die 'Failed in service_example.sh' $?

