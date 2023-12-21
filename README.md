# satun_helloworld
SEGA Saturn HelloWorld with SBL

Based on smpdbg10 SBL sample code.

- How to build :

rm -rf * && cmake -DCMAKE_INSTALL_PREFIX=/saturn .. && make && make install

(see https://github.com/willll/saturn-docker for a toolchain)

- Build in DEBUG

rm -rf * && cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_TOOLCHAIN_FILE=$SATURN_CMAKE/sega_saturn.cmake \
      -DCMAKE_INSTALL_PREFIX=/saturn/ .. && make && make install

- Where sources shall be stored:

addr2line -a 0x60055be -p -i -f -C -e ./helloworld.elf

- Screenshot

![Alt text](pics/screenshot_Kronos_2.3.1.png?raw=true "Kronos v2.3.1")
