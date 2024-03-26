#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int compare(const void *, const void *);
bool is_cycle(int, int);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count++].loser = j;
                }
            }
        }
    }
    return;
}

// Compare between the margain of win for two pairs with inverse logic for quick sort to sort in decreasing order
int compare(const void *e1, const void *e2)
{
    pair x = *((pair *) e1), y = *((pair *) e2);
    if (preferences[x.winner][x.loser] - preferences[x.loser][x.winner] >
        preferences[y.winner][y.loser] - preferences[y.loser][y.winner])
        return -1; // the first element is greater
    if (preferences[x.winner][x.loser] - preferences[x.loser][x.winner] <
        preferences[y.winner][y.loser] - preferences[y.loser][y.winner])
        return 1; // the first element is smaller
    return 0;     // they are equal
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare);
    return;
}

bool is_cycle(int start, int end)
{
    bool visited[MAX] = {false};

    int stack[MAX], top = -1, element;
    stack[++top] = start;

    while (top != -1)
    {
        element = stack[top--];
        if (element == end)
        {
            return true;
        }
        for (int i = 0; i < candidate_count; i++)
        {
            if (!visited[i])
            {
                bool adjecent = false;
                for (int j = 0; j < pair_count; j++)
                {
                    if (locked[pairs[j].winner][pairs[j].loser] && pairs[j].winner == element && pairs[j].loser == i)
                    {
                        adjecent = true;
                        break;
                    }
                }
                if (adjecent)
                {
                    visited[i] = true;
                    stack[++top] = i;
                }
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool locks[MAX] = {false};
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                locks[i] = true;
            }
        }
        if (!locks[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
