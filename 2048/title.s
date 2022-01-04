    .data

title:  .string 27, "[?25l", 27, "[30;48;5;226m", 27, "[2J", 27, "[0m",  27, "[0;0;H"
        .string 27, "[48;5;15m"
        .string 27, "[2;5;H",  "        ",  27, "[6C", "        "
        .string 27, "[3;3;H",  "    ",  27, "[4C", "    ", 27, "[2C", "            "
        .string 27, "[4;11;H", "    ",  27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[5;7;H", "        ",  27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[6;3;H", "        ",  27, "[6C", "    ", 27, "[4C", "    "
        .string 27, "[7;3;H", "    ",  27, "[10C", "            "
        .string 27, "[8;3;H",  "            ",  27, "[4C", "        "

        .string 27, "[10;3;H",  "    ",  27, "[4C", "    ", 27, "[4C", "        "
        .string 27, "[11;3;H",  "    ",  27, "[4C", "    ", 27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[12;3;H",  "    ",  27, "[4C", "    ", 27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[13;3;H",  "            ",  27, "[4C", "        "
        .string 27, "[14;5;H",  "          ",  27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[15;11;H",  "    ",  27, "[2C", "    ", 27, "[4C", "    "
        .string 27, "[16;11;H",  "    ",  27, "[4C", "        "
        .string 27, "[17;2;H", 27, "[30;48;5;226m", 27, "[38;5;0m", "Press: Enter or D on keypad", 0

right:   .string 27, "[2C", 0

    .text
    .global make_title


    .global output_string

    .export LCD_setCursor
    .export LCD_print

ptr_to_title:   .word title


make_title:
	STMFD SP!,{lr, r4-r11}

    ldr r0, ptr_to_title
    bl output_string

	LDMFD sp!, {lr, r4-r11}
	mov pc, lr
