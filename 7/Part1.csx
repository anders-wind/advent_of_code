
string line;
var dict = new Dictionary<char, HashSet<char>>();
while ((line = Console.ReadLine()) != null && line != "")
{
    var from = line[5];
    var to = line[36];
    if (!dict.ContainsKey(to))
    {
        dict.Add(to, new HashSet<char> { });
    }
    if (!dict.ContainsKey(from))
    {
        dict.Add(from, new HashSet<char> { });
    }
    dict[to].Add(from);
    Console.WriteLine(from + " " + to);
}
var taken = new HashSet<char>();
var left = dict.Keys.ToList();
var sb = new StringBuilder();
while (left.Any())
{
    var elements = left.Where(x => dict[x].All(y => taken.Contains(y)));
    var min = elements.Min();
    sb.Append(min);
    left.Remove(min);
    taken.Add(min);
}
Console.WriteLine(sb.ToString().ToString());