for i in `ls -d */`; do
	echo "$i"
	cd "$i"
	val=$(krun p1.cpp)
	ans=$(cat p1.txt)
	if [ $val != $ans ]; then
		echo "p1 wrong"
	fi
	val=$(krun p2.cpp)
	ans=$(cat p2.txt)
	if [ $val != $ans ]; then
		echo "p2 wrong"
	fi
	cd ..
done
