char temp[4];

void shift_right(char *array, int start, int stop){
    int i = 0;
    while(i < 4){
        temp[i] = 0;
        i++;
    }
    int j = 3;
    i = stop-1;

    while(i >= start){
        if(array[i] != 0){
            temp[j] = array[i];
            j--;
        }
        i--;
    }

    i = start;
    j = 0;
    while(j < stop-start){
        array[i] = temp[j];
        i++;j++;
    }
}

void shift_right_op(char *array){
    shift_right(array, 0, 4);
    shift_right(array, 4, 8);
    shift_right(array, 8, 12);
    shift_right(array, 12, 16);
}
