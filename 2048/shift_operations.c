#define ROW_LENGTH 4

char temp1[ROW_LENGTH];
char temp2[ROW_LENGTH];
void empty_arr(char *arr){
    int i = 0;
    while(i < ROW_LENGTH){
        arr[i] = 0;
        i++;
    }
}

void copy_row(char *copy, char *array, char start, char stop){
    while(start < stop){
        *copy = array[start];
        copy++;
        start++;
    }
}

void replace_row(char *array, char *replace, char start, char stop){
    while(start < stop){
        array[start] = *replace;
        replace++;
        start++;
    }
}

void copy_col(char *copy, char *array, char start, char stop){
    while(start <= stop){
        *copy = array[start];
        copy++;
        start+=ROW_LENGTH;
    }
}

void replace_col(char *array, char *replace, char start, char stop){
    while(start <= stop){
        array[start] = *replace;
        replace++;
        start+=ROW_LENGTH;
    }
}

int check_move(char *array){
    int x, y;

    for(y = 0; y<ROW_LENGTH; y++){
        for(x = 0; x<ROW_LENGTH; x++, array++){
            if(*array){
                if(y < ROW_LENGTH-1){
                    if(*array == *(array + ROW_LENGTH)){
                        return 1;
                    }
                }
                if(y > 0){
                    if(*array == *(array - ROW_LENGTH)){
                        return 1;
                    }
                }
                if(x < ROW_LENGTH-1){
                    if(*array == *(array + 1)){
                        return 1;
                    }
                }

                if(x > 0){
                    if(*array == *(array - 1)){
                        return 1;
                    }
                }
            }
            else{
                return 1;
            }
        }
    }

    return 0;
}

void shift_right(char *shifted, char *toshift){
    int i = ROW_LENGTH-1;
    int j = i;
    while(i >= 0){
        if(toshift[i] != 0){
            shifted[j] = toshift[i];
            j--;
        }
        i--;
    }
    while(j >= 0){
        shifted[j] = 0;
        j--;
    }
}

int combine_right(char *arr){
    int score = 0;
    int i = ROW_LENGTH-1;

    while(i > 0){
        if(arr[i] > 0 && arr[i] == arr[i-1]){
            arr[i]++;
            score += (1<<arr[i]);
            arr[i-1] = 0;
        }
        i--;
    }
    return score;
}

void shift_left(char *shifted, char *toshift){
    int i = 0;
    int j = 0;
    while(i < ROW_LENGTH){
        if(toshift[i] != 0){
            shifted[j] = toshift[i];
            j++;
        }
        i++;
    }
    while(j < ROW_LENGTH){
        shifted[j] = 0;
        j++;
    }
}

int combine_left(char *arr){
    int score = 0;
    int i = 0;

    while(i < ROW_LENGTH-1){
        if(arr[i] > 0 && arr[i] == arr[i+1]){
            arr[i]++;
            score += (1<<arr[i]);
            arr[i+1] = 0;
        }
        i++;
    }
    return score;
}

int check_move_right(char *array){
    int x, y;
    for(y = 0; y < ROW_LENGTH; y++){
        for(x = 0; x < ROW_LENGTH-1; x++, array++){
            if((*array != 0 && *array == *(array+1)) || (*array != 0 && *(array+1) == 0)){
                return 1;
            }
        }
        array++;
    }
    return 0;
}

int check_move_left(char *array){
    int x, y;
    for(y = 0; y < ROW_LENGTH; y++){
        for(x = 0; x < ROW_LENGTH-1; x++, array++){
            if((*array != 0 && *array == *(array+1)) || (*array == 0 && *(array+1) != 0)){
                return 1;
            }
        }
        array++;
    }
    return 0;
}

int check_move_down(char *array){
    int x, y;
    for(y = 0; y < ROW_LENGTH-1; y++){
        for(x = 0; x < ROW_LENGTH; x++, array++){
            if((*array != 0 && *array == *(array+ROW_LENGTH)) || (*array != 0 && *(array+ROW_LENGTH) == 0)){
                return 1;
            }
        }
    }
    return 0;
}

int check_move_up(char *array){
    int x, y;
    char a, b;
    for(y = 0; y < ROW_LENGTH-1; y++){
        for(x = 0; x < ROW_LENGTH; x++, array++){
            a = *array;
            b = *(array-ROW_LENGTH);
            if((*array != 0 && *array == *(array+ROW_LENGTH)) || (*array == 0 && *(array+ROW_LENGTH) != 0)){
                return 1;
            }
        }
    }
    return 0;
}

int shift_right_op(char *array){
    int score = 0;
    int i = 0;
    int stop = ROW_LENGTH*4;
    while(i < stop){
        copy_row(temp1, array, i, i+ROW_LENGTH);
        shift_right(temp2, temp1);
        score += combine_right(temp2);
        shift_right(temp1, temp2);
        replace_row(array, temp1, i, i+ROW_LENGTH);
        i+=ROW_LENGTH;
    }
    return score;
}

int shift_left_op(char *array){
    int score = 0;
    int i = 0;
    int stop = ROW_LENGTH*4;
    while(i < stop){
        copy_row(temp1, array, i, i+ROW_LENGTH);
        shift_left(temp2, temp1);
        score += combine_left(temp2);
        shift_left(temp1, temp2);
        replace_row(array, temp1, i, i+ROW_LENGTH);
        i+=ROW_LENGTH;
    }
    return score;
}

int shift_down_op(char *array){
    int score = 0;
    int i = 0;
    int stop = ROW_LENGTH;
    while(i < stop){
        copy_col(temp1, array, i, i+(ROW_LENGTH*ROW_LENGTH)-ROW_LENGTH);
        shift_right(temp2, temp1);
        score += combine_right(temp2);
        shift_right(temp1, temp2);
        replace_col(array, temp1, i, i+(ROW_LENGTH*ROW_LENGTH)-ROW_LENGTH);
        i++;
    }
    return score;
}

int shift_up_op(char *array){
    int score = 0;
    int i = 0;
    int stop = ROW_LENGTH;
    while(i < stop){
        copy_col(temp1, array, i, i+(ROW_LENGTH*ROW_LENGTH)-ROW_LENGTH);
        shift_left(temp2, temp1);
        score += combine_left(temp2);
        shift_left(temp1, temp2);
        replace_col(array, temp1, i, i+(ROW_LENGTH*ROW_LENGTH)-ROW_LENGTH);
        i++;
    }
    return score;
}
