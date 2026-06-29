#include <stdio.h>
#include <string.h>

int main() {
    char verbe[20], *p = verbe;
    int taille;
    FILE *fp;
    fp = fopen("essai.txt", "w");

    char *pronomCompose[] = {"J'", "Tu", "Il/Elle", "Nous", "Vous", "Ils/Elles"};
    char *pronom[] = {"Je", "Tu", "Il/Elle", "Nous", "Vous", "Ils/Elles"};
    char *termPresent[] = {"e", "es", "e", "ons", "ez", "ent"};
    char *termFutur[] = {"erai", "eras", "era", "erons", "erez", "eront"};
    char *termImparfait[] = {"ais", "ais", "ait", "ions", "iez", "aient"};
    char *termPasse[] = {"ai", "as", "a", "ames", "ates", "erent"};
    char *auxiliaireAvoirPresent[] = {"ai", "as", "a", "avons", "avez", "ont"};
    char *auxiliaireAvoirImparfait[] = {"avais", "avais", "avait", "avions", "aviez", "avaient"};
    char *auxiliaireAvoirPasse[] = {"eu", "eus", "eut", "eumes", "eutes", "eurent"};
    char *auxiliaireAvoirFutur[] = {"aurai", "auras", "aura", "aurons", "aurez", "auront"};
    char *termParticipePasse[] = {"e", "e", "e", "e", "e", "e"};
    int i, j;

    printf("Entrer un verbe\n\n");
    scanf("%s", verbe);

    taille = strlen(verbe);

    if (verbe[taille - 1] == 'r' && verbe[taille - 2] == 'e') {
        printf("Bon choix !\n\n");

        fprintf(fp, "\t****Present simple****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termPresent[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t****Futur Simple****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termFutur[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t****Passe simple****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termPasse[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t****Imparfait****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termImparfait[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t****Passe compose****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirPresent[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t****Plus-que-Parfait****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirImparfait[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\t****Passe Anterieur****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirPasse[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\t****Futur Anterieur****\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirFutur[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

    } else if (verbe[taille - 1] == 'r' && verbe[taille - 2] == 'i') {
        char *termPresent[] = {"is", "is", "it", "issons", "issez", "issent"};
        char *termFutur[] = {"irai", "iras", "ira", "irons", "irez", "iront"};
        char *termImparfait[] = {"issais", "issais", "issait", "issions", "issiez", "issaient"};
        char *termPasse[] = {"is", "is", "it", "imes", "ites", "irent"};
        char *termParticipePasse[] = {"i", "i", "i", "i", "i", "i"};

        fprintf(fp, "\t***Present simple*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termPresent[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t***Futur Simple*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termFutur[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t***Passe simple*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termPasse[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t***Imparfait*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronom[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termImparfait[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t***Passe compose*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirPresent[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\n");
        fprintf(fp, "\t***Plus-que-Parfait*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirImparfait[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\t***Passe Anterieur*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirPasse[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

        fprintf(fp, "\t***Futur Anterieur*\n");
        for (i = 0; i < 6; i++) {
            fprintf(fp, "%s  ", pronomCompose[i]);
            fprintf(fp, "%s  ", auxiliaireAvoirFutur[i]);
            for (j = 0; j <= taille - 3; j++) {
                fprintf(fp, "%c", verbe[j]);
            }
            fprintf(fp, "%s\n", termParticipePasse[i]);
        }

    } else {
        printf("T'as pas fait le primaire toi\n");
    }

    fclose(fp);
    return 0;
}
