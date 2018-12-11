var twos = 0;
var threes = 0;
string line;
while ((line = Console.ReadLine()) != null && line != "")
{
    var set = new Dictionary<char, int>();
    for(int i = 0; i < line.Length; i++) {
        var ch = line[i];
        if(set.ContainsKey(ch)){
            set[ch]++;
        } else {
            set[ch] = 1;
        }
    }
    if (set.Any(x => x.Value == 2)) twos++;
    if (set.Any(x => x.Value == 3)) threes++;
}
Console.WriteLine(twos*threes);