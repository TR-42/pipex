#!/bin/sh

CMD0='grep a'
CMD1='grep b'
CMD2='grep c'

EXPECTED_FNAME='expected'
ACTUAL_FNAME='actual'

INPUT1='abvcoa
avaovcbnoavnoav
veanovcnaoknvpavnp
fenfosievs
efsoiefoiesv
sefeofnosgv
knogrognr'
INPUT2='brcaboicba
gbwr
gbregagc
bhwrebrfewfewaherha'

cd `dirname $0`
cd ..

make bonus || exit $?

rm -f $ACTUAL_FNAME $EXPECTED_FNAME

./pipex here_doc EOF "$CMD0" "$CMD1" "$CMD2" $ACTUAL_FNAME << _EOF
$INPUT1
EOF
_EOF

echo "$INPUT1" | $CMD0 | $CMD1 | $CMD2 >> $EXPECTED_FNAME

./pipex here_doc EOF "$CMD0" "$CMD1" "$CMD2" $ACTUAL_FNAME << _EOF
$INPUT2
EOF
_EOF

echo "$INPUT2" | $CMD0 | $CMD1 | $CMD2 >> $EXPECTED_FNAME

diff $EXPECTED_FNAME $ACTUAL_FNAME || exit 1
