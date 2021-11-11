// algorithm made and found by yosh, simply drag and drop your brsar on the executable / python script, or type all of this in a terminal -> "Every-Game-brsar.exe" "my file.brsar"
#include <stdio.h>
unsigned long long brsar(char * file);

int main(int argc, char *argv[])
{
  printf("%s\n", argv[1]);
  if (argc < 2) // if the brsar is not given
  {
     printf("please add your filename as argument when launching this exe\nit's exactly what you make when doing drag and drop\npress enter to quit...");
     getchar();
  }
  else
  {
    printf("Successfully made %I64u brstm to their max size! (2GB)\npress enter to quit...\n", brsar(argv[1]));
    getchar();
  }
  return 0;
}

unsigned long long brsar(char * file)
{
    unsigned long long cursor = 0, cursor_save, number = 0, max_offset = 0x1f7b00;  // Super Smash Bros Brawl farest entry
    FILE *pointer;
    char readchar[6];
    char brstm_max_size[] = {"\x7f\xff\xff\xff"};  // max size of an unsigned hex float
    pointer = fopen(file, "r+b");
    printf("going through %s...\n", file);
    if (pointer == NULL) { printf("couldn't open >%s< for write access.\npress enter to exit...\n",file); getchar();} // this shouldn't happen
    else {
	fseek(pointer, 0L, SEEK_END);
    unsigned long long file_length = ftell(pointer); //stores file size
    if (file_length > 500000000) {max_offset = 0x6d9500;}  // Dragon Ball Z Budokai Tenkaichi 2 has a 1 GB brsar with entries really far
    while (cursor < max_offset)
    {
        fseek(pointer, cursor, SEEK_SET);
        cursor ++;
        fread(readchar, 1, 6, pointer);  /* reads 6 bytes and look if it's .brstm */
        // printf(">%c %c %c %c %c %c<\n", readchar[0], readchar[1], readchar[2], readchar[3], readchar[4], readchar[5]);
        if (readchar[0] == '.' && readchar[1] == 'b' && readchar[2] == 'r' && readchar[3] == 's' && readchar[4] == 't' && readchar[5] == 'm')
        {
            cursor_save = cursor;
            number ++;
            while (readchar[0] != '\xff' || readchar[1] != '\xff' || readchar[2] != '\xff' || readchar[3] != '\xff')
            {
                cursor --;
                fread(readchar, 1, 4, pointer);
                fseek(pointer, cursor, SEEK_SET);
            }
            if (number % 100 == 0)
            {
                printf(">fixed %I64u brstm...<\n", number); // on other compilators it's %llu
            }
            cursor -= 7;  // always FF FF FF FF eight bytes after the brstm max size
            fseek(pointer, cursor, SEEK_SET);  /* seek to the brstm max size offset */
            fwrite(&brstm_max_size, 1, 4, pointer);  /* write 7F FF FF FF which is 2 GB */
            cursor = cursor_save;
        }
    } } // closes the while and the else statement
    fclose(pointer);
    return number;
}
