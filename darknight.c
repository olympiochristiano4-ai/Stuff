#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ANSI color codes
#define GREEN   "\033[0;32m"
#define BGREEN  "\033[1;32m"
#define RED     "\033[0;31m"
#define BRED    "\033[1;31m"
#define CYAN    "\033[0;36m"
#define BCYAN   "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define DIM     "\033[2m"
#define RESET   "\033[0m"
#define CLEAR   "\033[2J\033[H"

// Game settings
#define CODE_LENGTH 5
#define MAX_ATTEMPTS 6
#define NUM_CHARS 8

// Available "hex-like" characters for the code
char charset[] = {'A', 'B', 'C', 'D', 'E', 'F', '1', '2'};

typedef struct {
    char code[CODE_LENGTH + 1];
    char attempts[MAX_ATTEMPTS][CODE_LENGTH + 1];
    int correct_pos[MAX_ATTEMPTS];   // good char, good position
    int correct_char[MAX_ATTEMPTS];  // good char, wrong position
    int num_attempts;
    int won;
} GameState;

void type_effect(const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay_ms * 1000);
    }
}

void print_banner() {
    printf(CLEAR);
    printf(BGREEN);
    type_effect("  ██████╗  █████╗ ██████╗ ██╗  ██╗███╗  ██╗██╗ ██████╗ ██╗  ██╗████████╗\n", 1);
    type_effect("  ██╔══██╗██╔══██╗██╔══██╗██║ ██╔╝████╗ ██║██║██╔════╝ ██║  ██║╚══██╔══╝\n", 1);
    type_effect("  ██║  ██║███████║██████╔╝█████╔╝ ██╔██╗██║██║██║  ███╗███████║   ██║   \n", 1);
    type_effect("  ██║  ██║██╔══██║██╔══██╗██╔═██╗ ██║╚████║██║██║   ██║██╔══██║   ██║   \n", 1);
    type_effect("  ██████╔╝██║  ██║██║  ██║██║  ██╗██║  ███║██║╚██████╔╝██║  ██║   ██║   \n", 1);
    type_effect("  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝   \n", 1);
    printf(RESET);
    printf(DIM GREEN "                     [ BREACH PROTOCOL v2.4 - ocsir@DARKNIGHT ]\n" RESET);
    printf(DIM GREEN "  ─────────────────────────────────────────────────────────────────────\n" RESET);
    printf("\n");
}

void generate_code(char *code) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = charset[rand() % NUM_CHARS];
    }
    code[CODE_LENGTH] = '\0';
}

void analyze_attempt(GameState *gs, int attempt_idx) {
    char *secret = gs->code;
    char *attempt = gs->attempts[attempt_idx];
    int correct_pos = 0, correct_char = 0;

    int secret_used[CODE_LENGTH] = {0};
    int attempt_used[CODE_LENGTH] = {0};

    // First pass: correct position
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (attempt[i] == secret[i]) {
            correct_pos++;
            secret_used[i] = 1;
            attempt_used[i] = 1;
        }
    }

    // Second pass: correct char, wrong position
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (attempt_used[i]) continue;
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (secret_used[j]) continue;
            if (attempt[i] == secret[j]) {
                correct_char++;
                secret_used[j] = 1;
                break;
            }
        }
    }

    gs->correct_pos[attempt_idx] = correct_pos;
    gs->correct_char[attempt_idx] = correct_char;
}

void print_board(GameState *gs) {
    printf(GREEN "  ┌─────────────────────────────────────────────┐\n" RESET);
    printf(GREEN "  │" BCYAN "  TARGET: " RESET);
    printf(DIM GREEN);
    for (int i = 0; i < CODE_LENGTH; i++) printf("?? ");
    printf(RESET);
    printf(GREEN "               │\n" RESET);
    printf(GREEN "  │  CHARSET: " RESET);
    printf(YELLOW);
    for (int i = 0; i < NUM_CHARS; i++) printf("%c  ", charset[i]);
    printf(RESET GREEN "    │\n" RESET);
    printf(GREEN "  ├───────────────────────────────┬─────────────┤\n" RESET);
    printf(GREEN "  │" RESET "  ATTEMPT              SEQUENCE " GREEN "│" RESET "  ██  ░░   " GREEN "│\n" RESET);
    printf(GREEN "  ├───────────────────────────────┼─────────────┤\n" RESET);

    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        printf(GREEN "  │" RESET);
        printf(DIM GREEN "  [%d/%d]  " RESET, i + 1, MAX_ATTEMPTS);

        if (i < gs->num_attempts) {
            // Print each char with color based on result
            char *att = gs->attempts[i];
            char *sec = gs->code;

            // Recompute per-char coloring
            int secret_used[CODE_LENGTH] = {0};
            int att_color[CODE_LENGTH] = {0}; // 2=green, 1=yellow, 0=dim

            // Green pass
            for (int k = 0; k < CODE_LENGTH; k++) {
                if (att[k] == sec[k]) {
                    att_color[k] = 2;
                    secret_used[k] = 1;
                }
            }
            // Yellow pass
            for (int k = 0; k < CODE_LENGTH; k++) {
                if (att_color[k] == 2) continue;
                for (int m = 0; m < CODE_LENGTH; m++) {
                    if (secret_used[m]) continue;
                    if (att[k] == sec[m]) {
                        att_color[k] = 1;
                        secret_used[m] = 1;
                        break;
                    }
                }
            }

            for (int k = 0; k < CODE_LENGTH; k++) {
                if (att_color[k] == 2)      printf(BGREEN "%c " RESET, att[k]);
                else if (att_color[k] == 1) printf(YELLOW "%c " RESET, att[k]);
                else                        printf(DIM "%c " RESET, att[k]);
            }

            printf(GREEN " │" RESET);
            printf(BGREEN "  ██:%d  " RESET, gs->correct_pos[i]);
            printf(YELLOW "░░:%d" RESET, gs->correct_char[i]);
            printf(GREEN "   │\n" RESET);
        } else {
            printf(DIM GREEN "  -  -  -  -  -         " RESET);
            printf(GREEN "│             │\n" RESET);
        }
    }

    printf(GREEN "  └───────────────────────────────┴─────────────┘\n" RESET);
    printf(DIM GREEN "    " BGREEN "██" RESET DIM GREEN " = bon emplacement   " RESET YELLOW "░░" RESET DIM GREEN " = bon caractère\n\n" RESET);
}

int validate_input(char *input) {
    if (strlen(input) != CODE_LENGTH) return 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        input[i] = input[i] >= 'a' && input[i] <= 'z' ? input[i] - 32 : input[i];
        int valid = 0;
        for (int j = 0; j < NUM_CHARS; j++) {
            if (input[i] == charset[j]) { valid = 1; break; }
        }
        if (!valid) return 0;
    }
    return 1;
}

void glitch_effect() {
    char glitch_chars[] = "█▓▒░╔╗╚╝╠╣╦╩";
    printf(BRED);
    for (int i = 0; i < 3; i++) {
        printf("  ");
        for (int j = 0; j < 20; j++) {
            printf("%c", glitch_chars[rand() % 13]);
            fflush(stdout);
            usleep(15000);
        }
        printf("\r");
        fflush(stdout);
        usleep(80000);
    }
    printf(RESET);
}

void win_animation(char *code) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(BGREEN "  >>> ACCESS GRANTED <<< " RESET "\r");
        fflush(stdout); usleep(300000);
        printf(DIM GREEN  "  >>> ACCESS GRANTED <<< " RESET "\r");
        fflush(stdout); usleep(300000);
    }
    printf("\n\n");
    type_effect(BGREEN "  ╔══════════════════════════════════════╗\n" RESET, 5);
    type_effect(BGREEN "  ║      BREACH SUCCESSFUL               ║\n" RESET, 5);
    printf(BGREEN "  ║  CODE: " RESET BCYAN);
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf("%c ", code[i]);
        fflush(stdout);
        usleep(150000);
    }
    printf(BGREEN "       ║\n" RESET);
    type_effect(BGREEN "  ║      ICE neutralisé. Bienvenue.      ║\n" RESET, 5);
    type_effect(BGREEN "  ╚══════════════════════════════════════╝\n" RESET, 5);
}

void lose_animation(char *code) {
    glitch_effect();
    printf("\n");
    type_effect(BRED "  ╔══════════════════════════════════════╗\n" RESET, 5);
    type_effect(BRED "  ║      CONNECTION TERMINATED            ║\n" RESET, 5);
    printf(BRED "  ║  CODE ÉTAIT: " RESET YELLOW);
    for (int i = 0; i < CODE_LENGTH; i++) printf("%c ", code[i]);
    printf(BRED "        ║\n" RESET);
    type_effect(BRED "  ║      ICE actif. Trace en cours...     ║\n" RESET, 5);
    type_effect(BRED "  ╚══════════════════════════════════════╝\n" RESET, 5);
}

int main() {
    srand(time(NULL));
    GameState gs;
    char input[64];
    char play_again;

    do {
        // Init game state
        memset(&gs, 0, sizeof(GameState));
        generate_code(gs.code);
        gs.num_attempts = 0;
        gs.won = 0;

        print_banner();
        type_effect(CYAN "  Infiltration du système en cours", 40);
        type_effect("...\n" RESET, 200);
        usleep(400000);
        type_effect(GREEN "  Séquence de breach initiée.\n" RESET, 30);
        usleep(300000);
        type_effect(DIM GREEN "  Trouvez le code de " RESET BCYAN "5 caractères" RESET DIM GREEN " parmi : " RESET YELLOW "A B C D E F 1 2\n\n" RESET, 20);
        usleep(200000);

        while (gs.num_attempts < MAX_ATTEMPTS && !gs.won) {
            print_board(&gs);

            printf(GREEN "  > INJECT SEQUENCE: " RESET BCYAN);
            fflush(stdout);

            if (fgets(input, sizeof(input), stdin) == NULL) break;
            input[strcspn(input, "\n")] = '\0';

            printf(RESET);

            if (!validate_input(input)) {
                printf(BRED "  [ERR] Séquence invalide. Utilisez exactement 5 caractères parmi A B C D E F 1 2\n\n" RESET);
                usleep(800000);
                printf(CLEAR);
                print_banner();
                continue;
            }

            strncpy(gs.attempts[gs.num_attempts], input, CODE_LENGTH);
            gs.attempts[gs.num_attempts][CODE_LENGTH] = '\0';
            analyze_attempt(&gs, gs.num_attempts);

            if (gs.correct_pos[gs.num_attempts] == CODE_LENGTH) {
                gs.won = 1;
            }

            gs.num_attempts++;
            printf(CLEAR);
            print_banner();
        }

        print_board(&gs);

        if (gs.won) {
            win_animation(gs.code);
        } else {
            lose_animation(gs.code);
        }

        printf("\n" DIM GREEN "  Rejouer ? (o/n) : " RESET BCYAN);
        scanf(" %c", &play_again);
        getchar();
        printf(RESET "\n");
        printf(CLEAR);

    } while (play_again == 'o' || play_again == 'O');

    type_effect(DIM GREEN "\n  Session terminée. Déconnexion...\n\n" RESET, 30);

    return 0;
}
