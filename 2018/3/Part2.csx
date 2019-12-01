var takenBy = new int[1000,1000];
var unbroken = new HashSet<int>();
string line;
while ((line = Console.ReadLine()) != null && line != "")
{
    var at = line.IndexOf('@');
    var comma = line.IndexOf(',');
    var colon = line.IndexOf(':');
    var by = line.IndexOf('x');
    var end = line.Length;

    int x = Int32.Parse(line.Substring(at+1, comma-at-1).Trim());
    int y = Int32.Parse(line.Substring(comma+1, colon-comma-1).Trim());
    int w = Int32.Parse(line.Substring(colon+1, by-colon-1).Trim());
    int h = Int32.Parse(line.Substring(by+1, end-by-1).Trim());

    int claim = Int32.Parse(line.Substring(1, at-2).Trim());
    unbroken.Add(claim);
    
    for (int i = x; i<x+w; i++) {
        for (int j = y; j<y+h; j++) {
            if (takenBy[i,j]==0) {
                takenBy[i,j] = claim;
            } else {
                unbroken.Remove(claim);
                unbroken.Remove(takenBy[i,j]);
            }
        }
    }
}
Console.WriteLine(unbroken.Single());