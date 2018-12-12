
int ruleLength = 5;
string line;
string state = "....." + Console.ReadLine().Remove(0, 15) + ".....";
Console.ReadLine();
var ruleSet = new Dictionary<string, bool>();
while ((line = Console.ReadLine()) != null && line != "")
{
    var rule = line.Substring(0, ruleLength);
    ruleSet.Add(rule, line.Substring(9, 1) == "#" ? true : false);
}
int result = state.Count(x => x == '#');
Console.WriteLine("\n0: " + state);
int offset = -state.IndexOf('#');
for (int i = 1; i <= 20; i++)
{
    StringBuilder newState = new StringBuilder(state);
    for (int j = 0; j < state.Length - 5; j++)
    {
        var match = state.Substring(j, 5);
        if (ruleSet.ContainsKey(match))
        {
            if (ruleSet[match])
            {
                newState.Replace(match[2], '#', j + 2, 1);
            }
            else
            {
                newState.Replace(match[2], '.', j + 2, 1);
            }
        }
        else
        {
            newState.Replace(match[2], '.', j + 2, 1);
        }
    }
    state = "." + newState.ToString() + ".";
    offset--;
    result += state.Count(x => x == '#');
    Console.WriteLine(i + ": " + state);
}

int resultId = 0;
for (int i = 0; i < state.Length; i++)
{
    if (state[i] == '#') resultId += i + offset;
}
Console.WriteLine(resultId);