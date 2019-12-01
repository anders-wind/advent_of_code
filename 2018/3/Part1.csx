var matrix = new int[1000,1000];
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

    for (int i = x; i<x+w; i++) {
        for (int j = y; j<y+h; j++) {
            matrix[i, j]++;
        }
    }
}
int total = 0;
for (int i = 0; i<1000; i++) {
    for (int j = 0; j<1000; j++) {
        if(matrix[i, j] >= 2) {
            total++;
        }
    }
}
Console.WriteLine(total);