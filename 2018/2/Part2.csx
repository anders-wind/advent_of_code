string line;
var set = new HashSet<string>();
while ((line = Console.ReadLine()) != null && line != "")
{
    var newSet = new HashSet<string>();
    for(int i = 0; i < line.Length; i++) {
        var without = line.Remove(i, 1);
        if(set.Contains(without)) {
            Console.WriteLine(without);
            return;
        } else {
            newSet.Add(without);
        }
    }
    set.UnionWith(newSet);
}