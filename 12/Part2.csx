
int ruleLength = 5;
string line;
string state = "......" + Console.ReadLine().Remove(0, 15) + ".....";
Console.ReadLine();
var ruleSet = new HashSet<string>();
while ((line = Console.ReadLine()) != null && line != "")
{
    var rule = line.Substring(0, ruleLength);
    if (line.Substring(9, 1) == "#")
    {
        ruleSet.Add(rule);
    }
}
Console.WriteLine("\n0: " + state);
long offset = -state.IndexOf('#');
long iterations = 50000;
for (long i = 1; i <= iterations; i++)
{
    StringBuilder newState = new StringBuilder(state);
    for (int j = 2; j < state.Length - 4; j++)
    {
        var match = state.Substring(j, 5);
        if (ruleSet.Contains(match))
        {
            newState.Replace(match[2], '#', j + 2, 1);
        }
        else
        {
            newState.Replace(match[2], '.', j + 2, 1);
        }
    }
    state = newState.ToString();
    var startIndex = state.IndexOf('#');
    if (startIndex != 6)
    {
        offset += startIndex - 6;
    }
    var endIndex = state.LastIndexOf('#');
    state = "....." + state.Substring(startIndex - 1, endIndex - startIndex + 2) + ".....";
    if (i % 10000 == 0)
    {
        Console.WriteLine(i + ": " + state);
    }
}
Console.WriteLine(iterations + ": " + state);
Console.WriteLine(iterations + ":" + offset);
offset = 49999999977;
long resultIdSum = 0;
for (int i = 0; i < state.Length; i++)
{
    if (state[i] == '#') resultIdSum += i + offset;
}
Console.WriteLine(resultIdSum);