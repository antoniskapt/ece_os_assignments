# OS - October 2023
# Quiz 1

mkdir quiz-1
mkdir quiz-1/myfiles

for i in {10413..10421}; do
	mkdir touch quiz-1/myfiles/folder$i
	touch -a "$((26-RANDOM%5)) November 2023"  quiz-1/myfiles/folder$i/file$i.txt
	done

ls -R

words=(banana chair tomato)

for i in {10413..10421}; do
	let "counter=0"
	counter=$(wc -l < "quiz-1/myfiles/folder$i/file$i.txt")
	while [ $counter -lt 20 ]; do
		rand=$((RANDOM%(21-counter)))
		for j in $(seq 1 $rand); do
			k=$((RANDOM%3))
			echo ${words[$k]} >> quiz-1/myfiles/folder$i/file$i.txt
		done
		counter=$((counter+rand))
	done
done

for i in {10413..10421}; do
	cat quiz-1/myfiles/folder$i/file$.txt; echo -e '\n'
	done

for i in {10413..10421}; do
	cat quiz-1/myfiles/folder$i/file$i.txt; echo -e '\n'
	done

touch quiz-1/report.txt

ls -R

for i in {10413..10421}; do
	find ~ -name file$i.txt >> quiz-1/report.txt
	for j in {0..2}; do
		result=$(grep -o -i ${words[$j]} quiz-1/myfiles/folder$i/file$i.txt | wc -l)
		echo -e "${words[$j]} $result" >> quiz-1/report.txt
	done
	echo -e '\n' >> quiz-1/report.txt
done

more quiz-1/report.txt

touch -a "24 November 2023" quiz-1/quiz1.log

ls -R

# history | tail -n +186 >> quiz-1/quiz1.log
