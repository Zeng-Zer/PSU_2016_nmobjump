#! /bin/bash

function check() {
    if [ "$?" == "1" ];
    then echo "KO"
    else echo "OK"
    fi
}

echo "graphics.so: "
diff <(./my_objdump ~/.froot/lib/libsfml-graphics.so.2.3) <(objdump -fs ~/.froot/lib/libsfml-graphics.so.2.3)
check
echo "system.so: "
diff <(./my_objdump ~/.froot/lib/libsfml-system.so) <(objdump -fs ~/.froot/lib/libsfml-system.so)
check
echo "audio.so: "
diff <(./my_objdump ~/.froot/lib/libsfml-audio.so) <(objdump -fs ~/.froot/lib/libsfml-audio.so)
check
echo "liblapin.a: "
diff <(./my_objdump ~/.froot/lib/liblapin.a) <(objdump -fs ~/.froot/lib/liblapin.a)
check
echo "main.o: "
diff <(./my_objdump src/main.o) <(objdump -fs src/main.o)
check
echo "my_objdump: "
diff <(./my_objdump my_objdump) <(objdump -fs my_objdump)
check
echo "my_malloc.so: "
diff <(./my_objdump ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so) <(objdump -fs ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so)
check
echo "firefox: "
diff <(./my_objdump /bin/firefox) <(objdump -fs /bin/firefox)
check
echo "ls: "
diff <(./my_objdump /bin/ls) <(objdump -fs /bin/ls)
check
echo "many file: "
diff <(./my_objdump my_objdump src/main.o ~/.froot/lib/libsfml-network.so ~/.froot/lib/liblapin.a) <(objdump -fs my_objdump src/main.o ~/.froot/lib/libsfml-network.so ~/.froot/lib/liblapin.a)
check
echo "double liblapin.a: "
diff <(./my_objdump ~/.froot/lib/liblapin.a ~/.froot/lib/liblapin.a) <(objdump -fs ~/.froot/lib/liblapin.a ~/.froot/lib/liblapin.a)
check
echo "32bit: "
diff <(./my_objdump ~/test/trash/obj32) <(objdump -fs ~/test/trash/obj32)
check
