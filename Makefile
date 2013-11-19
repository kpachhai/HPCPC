F = passlist/simplewords.txt

make:
	g++ -Wall convert_md5_txt.cpp -o convert_md5_txt -lcrypto -lssl
run:
	./convert_md5_txt $(F)
clean:
	rm -rf convert_md5_txt
