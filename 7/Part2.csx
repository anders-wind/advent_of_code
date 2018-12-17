
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
    //Console.WriteLine(from + " " + to);
}

public class Pair<T1, T2>
{
    public Pair(T1 t1, T2 t2)
    {
        Item1 = t1;
        Item2 = t2;
    }
    public T1 Item1 { get; set; }
    public T2 Item2 { get; set; }
}
var taken = new HashSet<char>();
var left = dict.Keys.ToHashSet();
int n = left.Count();
var sb = new StringBuilder();
var workers = new List<Pair<int, char>>();
var freeWorkers = 5;
int time = 0;
while (taken.Count() != n)
{
    if (left.Any())
    {
        var elements = left.Where(x => dict[x].All(y => taken.Contains(y))).OrderBy(z => z).Take(freeWorkers).ToList();
        int newWork = 0;
        for (int j = 0; j < freeWorkers && j < elements.Count(); j++)
        {
            workers.Add(new Pair<int, char>((int)elements[j] - 64, elements[j]));
            left.Remove(elements[j]);
            newWork++;
        }
        freeWorkers -= newWork;
    }

    var minTime = workers.Min(x => x.Item1);
    int freed = 0;
    for (int i = 0; i < minTime; i++)
    {
        time++;
        Console.Write(time + "  ");
        for (int j = 0; j < workers.Count(); j++)
        {
            Console.Write(workers[j].Item2 + " ");
            if (workers[j].Item1 != 0)
            {
                workers[j].Item1--;
            }

            if (workers[j].Item1 == 0)
            {
                sb.Append(workers[j].Item2);
                taken.Add(workers[j].Item2);
            }
        }
        Console.WriteLine();
    }
    freeWorkers += workers.Count(x => x.Item1 == 0);
    workers = workers.Where(x => x.Item1 != 0).ToList();
}
Console.WriteLine(sb.ToString());
Console.WriteLine(time);