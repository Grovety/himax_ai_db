mcumgr conn add testDK type="serial" connstring="COM11,baud=115200,mtu=1024"
pause
mcumgr -c testDK image list
pause
mcumgr -c testDK image upload ./build/objdet/zephyr/zephyr.signed.bin
pause
mcumgr -c testDK reset
pause