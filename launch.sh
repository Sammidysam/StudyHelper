# make if desired (variable is true)
# make variable can be true or false
make=true
if $make ;
then
	echo "Making..."
	make
	if [ $? == 0 ];
	then
		echo "Complete!"
		clear
	else
		echo "Error on completion!"
		for i in {1..2};
		do
			echo ""
		done
	fi
fi

# launch application
cd bin
./StudyHelper
