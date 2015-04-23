
for i in {1..100}
    do ifconfig en0 down;sleep 1; ifconfig en0 up;sleep 8;
        echo $i
done
