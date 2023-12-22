#include <cs50.h>
#include <stdio.h>

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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int strength_pairs[MAX * (MAX - 1) / 2];////strength of victory,

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int _strcmp(string s1, string s2);

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
        if (_strcmp(name, candidates[i]) == 0)
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
    for (int rank = 0; rank < candidate_count; rank++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            for (int i = rank; i < candidate_count; i++)
            {
                if (j != ranks[rank] && j == ranks[i])
                {
                    preferences[ranks[rank]][j] = preferences[ranks[rank]][j] + 1;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                strength_pairs[pair_count] = preferences[i][j] - preferences[j][i];
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count = pair_count + 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                strength_pairs[pair_count] = preferences[j][i] - preferences[i][j];
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair t;
    int tmp;
    int indx;
    for (int i = 0; i < pair_count - 1; i++)
    {
        indx = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (strength_pairs[i] < strength_pairs[j])
            {
                indx = j;
            }
        }
        if (indx != i)
        {
            tmp = strength_pairs[i];
            strength_pairs[i] = strength_pairs[indx];
            strength_pairs[indx] = tmp;

            t = pairs[i];
            pairs[i] = pairs[indx];
            pairs[indx] = t;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int l = 0;
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        int test = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                test++;
            }
        }
        if (test == 2)
        {
            l = 1;
        }
    }
    if (l != 1)
    {
        locked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = false;
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                int k;
                for (k = 0; k < candidate_count; k++)
                {
                    if (locked[k][i] == true)
                    {
                        break;
                    }
                }
                if (k == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                    return;
                }
            }
        }
    }
    return;
}

/**
 * _strcmp - compares two strings character by character
 * @s1: the first string
 * @s2: the second string
 *
 * Return: pointer to the destination string
 */
int _strcmp(string s1, string s2)
{
    int i = 0;

    while (s1[i] == s2[i])
    {
        if (s1[i] == '\0')
        {
            return (0);
        }
        i++;
    }
    return (s1[i] - s2[i]);
}