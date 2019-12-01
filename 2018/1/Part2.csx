var result = 0;
var set = new HashSet<int> { 0 };
var list = new List<int>();
string line;
while ((line = Console.ReadLine()) != null && line != "")
{
    var elem = int.Parse(line);
    result += elem;
    list.Add(elem);
    if (set.Contains(result))
    {
        Console.WriteLine(result);
        return;
    }
    else
    {
        set.Add(result);
    }
}
while (true)
{
    foreach (var x in list)
    {
        result += x;
        if (set.Contains(result))
        {
            Console.WriteLine(result);
            return;
        }
    }
}
