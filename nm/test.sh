#! /bin/bash

function check() {
    if [ "$?" == "1" ];
    then echo "KO"
    else echo "OK"
    fi
}

echo "graphics.so: "
diff <(./my_nm ~/.froot/lib/libsfml-graphics.so.2.3) <(nm ~/.froot/lib/libsfml-graphics.so.2.3)
check
echo "system.so: "
diff <(./my_nm ~/.froot/lib/libsfml-system.so) <(nm ~/.froot/lib/libsfml-system.so)
check
echo "audio.so: "
diff <(./my_nm ~/.froot/lib/libsfml-audio.so) <(nm ~/.froot/lib/libsfml-audio.so)
check
echo "liblapin.a: "
diff <(./my_nm ~/.froot/lib/liblapin.a) <(nm ~/.froot/lib/liblapin.a)
check
echo "main.o: "
diff <(./my_nm src/main.o) <(nm src/main.o)
check
echo "my_nm: "
diff <(./my_nm my_nm) <(nm my_nm)
check
echo "my_malloc.so: "
diff <(./my_nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so) <(nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so)
check
echo "firefox: "
diff <(./my_nm /bin/firefox) <(nm /bin/firefox)
check
