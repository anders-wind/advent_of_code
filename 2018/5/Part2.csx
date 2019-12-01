string line = Console.ReadLine();
var best = 100000000;
var bestL = ' ';
foreach (char ch in line.ToLower().Distinct()) {
    string chs = ch.ToString();
    string l = line.Replace(chs, "").Replace(chs.ToUpper(), "");
    bool converged = false;
    while(!converged) {
        converged = true;
        for (int i = 0; i<l.Length-1; i++) {
            if(l[i]!=l[i+1] && Char.ToLower(l[i]) == Char.ToLower(l[i+1])) {
                l = l.Remove(i,2);
                converged = false;
            }	
        }
    }
    if(l.Length < best) {
        bestL = ch;
        best = l.Length;
    }
}
Console.WriteLine(best);
Console.WriteLine(bestL);
