# keep open boolean
# if true will call read after launch
keepOpen=true

# keep open method
keepOpen(){
	for i in {1..2};
	do
		echo ""
	done
	echo "Launch complete!"
	echo "Press enter to close."
	read
}

# launch flags
flags="--exec-location bin"

# launch application method
launch(){
	bin/StudyHelper $flags
	if $keepOpen ; then keepOpen; fi
}

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

		# launch application
		launch
	else
		echo "Error on completion!"

		# keep open if wanted
		if $keepOpen ; then keepOpen; fi
	fi
else
	# launch application
	launch
fi
