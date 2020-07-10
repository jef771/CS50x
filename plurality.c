#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Passar pela lista da candidatos até achar um espaço vazio '\0'
    for (int i = 0; candidates[i].name != NULL; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
            break;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Var para armazenar o valor do maior número de votos
    int vote_count = 0;
    int counter = 1;
    // Array para armazenar o vencedor ou vencedores, com 9 elementos já que é o número MAX informado
    string winner[candidate_count];
    // Passar pelo array candidates até achar espaço vazio
    for (int i = 0; candidates[i].name != NULL; i++)
    {
        if (candidates[i].votes > vote_count)
        {
            vote_count = candidates[i].votes;
            // Troca os elementos do array winner pelo candidato considerado vencedor até o momento
            winner[0] = candidates[i].name;
        }
        else if (candidates[i].votes == vote_count)
        {
            // Caso o número de votos for igual ao número de votos armazenado o candidato ocupa outro lugar na lista
            winner[counter] = candidates[i].name;
            counter++;
        }

    }
    // Novamente pelo espaço vazio

    for (int i = 0; i < counter; i++)
    {
        // Se encontrar uma sring "nulo" o programa para
        printf("%s\n", winner[i]);

    }
    printf("\n");
}
