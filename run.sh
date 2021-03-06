if [ $# -gt 0 ]; then
	postfix=$1
	if [ $# -gt 1 ]; then
		skip=$2
		((skip=skip-1))
	else
		skip=0
	fi
else
	postfix=M
	skip=0
fi

cp mutators/mutator.Txl.$postfix mutator.Txl

while read line; do
	if [ $skip -gt 0 ]; then
		((skip=skip-1))
		continue
	fi
	echo $line
	subName=`basename $line`
	if [ -d mutation_out ]; then
		rm -rf mutation_out
	fi
	if [ -f gstats.xml ]; then
		rm -f gstats.xml
	fi
	rm -rf mutation_out_single
	mkdir mutation_out_single
	for single in `ls $line`; do
		if [[ $single == config.single*.cfg ]]; then
			valgrind ./Controller $line/$single
			cp -r mutation_out/* mutation_out_single/
			cp gstats.xml gstats.tmp.xml
		fi
	done
	if [ ! -d PUTs/$subName ]; then
		mkdir PUTs/$subName
	fi
	if [ -d PUTs/$subName/mutation_out_$postfix ]; then
		rm -rf PUTs/$subName/mutation_out_$postfix
	fi
	if [ -f PUTs/$subName/gstats_$postfix.xml ]; then
		rm -f PUTs/$subName/gstats_$postfix.xml
	fi
	cp -r mutation_out_single PUTs/$subName/mutation_out_$postfix
	cp gstats.xml PUTs/$subName/gstats_$postfix.xml
done < subjectList.txt
