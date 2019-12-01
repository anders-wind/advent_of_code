string l = Console.ReadLine();
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
Console.WriteLine(l.Length);