int _count = 0;

/*
 * swap
 */
void array_swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
/*
 * 二分法初始化
 */
void binary_init(int *array, int start, int end)
{
    int mid = (end + start)/2;
    if ((mid == start) || (mid == end)) {
        array[mid] = rand() % 100;
        return;
    }
    array[mid] = rand() % 100;
    _count ++;
    printf("start: %d, mid: %d, end: %d\n", start, mid, end);
    binary_init(array, start, mid);
    binary_init(array, mid, end);
}

/*
 * 快速排序
 */
void binary_sort(int *array, int start, int end)
{
    if (start == end) {
        return;
    }

    int key = array[start];
    int i = start + 1;
    int j = end;
    while (i < j) {
        if (array[i] > key) {
            array_swap(&array[i], &array[j]);
            j --;
        } else {
            i ++;
        }
        /* check end */
        if (i == j) {
            break;
        }
        if (array[j] < key) {
            array_swap(&array[i], &array[j]);
            i ++;
        }
        else {
            j --;
        }
        /* check end */
        if (i == j) {
            break;
        }
    }
    binary_sort(array, start, i - 1);
    binary_sort(array, i - 1, end);
}

/*
 * 二分法查找
 */
/* void binary_search(int *array) */
/* { */
/*     int mid = (end + start)/2; */
/* } */

void main()
{
    int array[32] = {0};
    binary_init(array, 0, 32);
    printf("all:%d\n", _count);
    for (int i = 0; i <= 31; i++) {
        printf("array[%d]: %d \n", i, array[i]);
    }

    binary_sort(array, 0, 31);
    printf("======================\n");
    for (int i = 0; i <= 31; i++) {
        printf("array[%d]: %d \n", i, array[i]);
    }
}
