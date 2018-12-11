string gString = "Guard #";
string bString = "begins";
string aString = "falls";
string wString = "wakes";
abstract class MessageBase
{
}
class GuardMessage : MessageBase
{
    public int guardId { get; set; }
}

class FallAsleepMessage : MessageBase
{
    public int minute { get; set; }
}

class WakeMessage : MessageBase
{
    public int minute { get; set; }
}

var lines = new List<string>();
var messages = new SortedDictionary<DateTime, MessageBase>();
string line;
while ((line = Console.ReadLine()) != null && line != "")
{
    DateTime date = DateTime.Parse(line.Substring(1, 16));
    int gIndex = line.IndexOf(gString);
    int bIndex = line.IndexOf(bString);
    if (gIndex != -1)
    {
        int guardId = Int32.Parse(line.Substring(gIndex + gString.Length, bIndex - (gIndex + gString.Length)).Trim());
        messages.Add(date, new GuardMessage { guardId = guardId });
        continue;
    }
    else if (line.IndexOf(aString) != -1)
    {
        messages.Add(date, new FallAsleepMessage { minute = date.Minute });
        continue;
    }
    else if (line.IndexOf(wString) != -1)
    {
        messages.Add(date, new WakeMessage { minute = date.Minute });
        continue;
    }
}
var sleepers = new Dictionary<int, int>();
var minutes = new Dictionary<int, int[]>();
int currentGuard = -1;
int currentStart = -1;
foreach (var message in messages)
{
    if (message.Value is GuardMessage)
    {
        currentGuard = (message.Value as GuardMessage).guardId;
        if (!sleepers.ContainsKey(currentGuard))
        {
            sleepers.Add(currentGuard, 0);
        }
        if (!minutes.ContainsKey(currentGuard))
        {
            minutes.Add(currentGuard, new int[60]);
        }
    }
    else if (message.Value is FallAsleepMessage)
    {
        currentStart = (message.Value as FallAsleepMessage).minute;
    }
    else
    {
        sleepers[currentGuard] += (message.Value as WakeMessage).minute - currentStart;
        for (int i = currentStart; i < (message.Value as WakeMessage).minute; i++)
        {
            minutes[currentGuard][i]++;
        }
    }
}
var superSleeper = sleepers.OrderByDescending(x =>
{
    return minutes[x.Key].Max();
}).First().Key;
var superTime = 0;
var maxTime = 0;
for (int i = 0; i < 60; i++)
{
    if (minutes[superSleeper][i] > maxTime)
    {
        superTime = i;
        maxTime = minutes[superSleeper][i];
    }
}
Console.WriteLine(superSleeper * superTime);
