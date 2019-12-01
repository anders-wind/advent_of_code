var result = 0;
string line;
while ((line = Console.ReadLine()) != null && line != "")
{
    result += int.Parse(line);
}
Console.WriteLine(result);