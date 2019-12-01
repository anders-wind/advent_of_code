public enum TrackType
{
    nothing,
    vertical,
    horizontal,
    intersect,
    crash,
    turn_right,
    turn_left,
}

int width = 0;
int height = 0;
string line;
var lines = new List<string>();
while ((line = Console.ReadLine()) != null && line != "")
{
    width = line.Length;
    height++;
    lines.Add(line);
}
public enum Direction
{
    up,
    down,
    left,
    right,
}
public class Cart
{
    public int id { get; set; }
    public int x { get; set; }
    public int y { get; set; }
    public Direction d { get; set; }
    public int state { get; set; }

    public override string ToString()
    {
        return $"{id}:[{x},{y}]";
    }
}
var comparer = Comparer<Cart>.Create((x, y) =>
    {
        var hDiff = x.y.CompareTo(y.y);
        if (hDiff != 0)
        {
            return hDiff;
        }
        return x.x.CompareTo(y.x);
    });
var carts = new SortedSet<Cart>(comparer);
var tracks = new TrackType[width, height];
int id = 0;
for (int i = 0; i < height; i++)
{
    var l = lines[i];
    for (int j = 0; j < width; j++)
    {
        var stuff = l[j];
        //Console.WriteLine($"[{j},{i}]" + stuff);
        switch (stuff)
        {
            case ' ':
                {
                    tracks[j, i] = TrackType.nothing;
                    break;
                }
            case '|':
                {
                    tracks[j, i] = TrackType.vertical;
                    break;
                }
            case '-':
                {
                    tracks[j, i] = TrackType.horizontal;
                    break;
                }
            case '+':
                {
                    tracks[j, i] = TrackType.intersect;
                    break;
                }
            case '/':
                {
                    tracks[j, i] = TrackType.turn_right;
                    break;
                }
            case '\\':
                {
                    tracks[j, i] = TrackType.turn_left;
                    break;
                }
            case '<':
                {
                    tracks[j, i] = TrackType.horizontal;
                    carts.Add(new Cart { x = j, y = i, d = Direction.left, state = 0, id = id++ });
                    break;
                }
            case '>':
                {
                    tracks[j, i] = TrackType.horizontal;
                    carts.Add(new Cart { x = j, y = i, d = Direction.right, state = 0, id = id++ });
                    break;
                }
            case '^':
                {
                    tracks[j, i] = TrackType.vertical;

                    carts.Add(new Cart { x = j, y = i, d = Direction.up, state = 0, id = id++ });
                    break;
                }
            case 'v':
                {
                    tracks[j, i] = TrackType.vertical;
                    carts.Add(new Cart { x = j, y = i, d = Direction.down, state = 0, id = id++ });
                    break;
                }
        }
    }
}

string[] map = new string[height];
for (int i = 0; i < height; i++)
{
    map[i] = new string(' ', width);
}

int original = carts.Count();
int ticks = 0;
bool crash = false;
while (!crash)
{
    ticks++;
    var newCarts = new SortedSet<Cart>(comparer);

    if (ticks % 100 == 0)
    {
        carts.ToList().ForEach(c => Console.Write($"{c} "));
        Console.WriteLine();//"\ntick: " + ticks);
    }
    int index = 0;
    var destroyed = new bool[original];
    foreach (var cart in carts)
    {
        if (destroyed[cart.id]) continue;
        var tile = tracks[cart.x, cart.y];
        var newX = cart.x;
        var newY = cart.y;
        var newD = cart.d;
        var newState = cart.state;
        switch (tile)
        {
            case TrackType.horizontal:
                if (cart.d == Direction.left) newX--;
                else if (cart.d == Direction.right) newX++;
                break;
            case TrackType.vertical:
                if (cart.d == Direction.up) newY--;
                else if (cart.d == Direction.down) newY++;
                break;
            case TrackType.intersect:
                if (cart.state == 0) // left
                {
                    if (cart.d == Direction.up)
                    {
                        newX--;
                        newD = Direction.left;
                    }
                    else if (cart.d == Direction.down)
                    {
                        newX++;
                        newD = Direction.right;
                    }
                    else if (cart.d == Direction.left)
                    {
                        newY++;
                        newD = Direction.down;
                    }
                    else if (cart.d == Direction.right)
                    {
                        newY--;
                        newD = Direction.up;
                    }
                }
                else if (cart.state == 1) // straight
                {
                    if (cart.d == Direction.up)
                    {
                        newY--;
                    }
                    else if (cart.d == Direction.down)
                    {
                        newY++;
                    }
                    else if (cart.d == Direction.left)
                    {
                        newX--;
                    }
                    else if (cart.d == Direction.right)
                    {
                        newX++;
                    }
                }
                else if (cart.state == 2)// right
                {
                    if (cart.d == Direction.up)
                    {
                        newX++;
                        newD = Direction.right;
                    }
                    else if (cart.d == Direction.down)
                    {
                        newX--;
                        newD = Direction.left;
                    }
                    else if (cart.d == Direction.left)
                    {
                        newY--;
                        newD = Direction.up;
                    }
                    else if (cart.d == Direction.right)
                    {
                        newY++;
                        newD = Direction.down;
                    }
                }
                newState = (cart.state + 1) % 3;
                // Console.WriteLine(cart + " " + tile + " " + cart.d);
                // Console.WriteLine("newX " + newX + " newY " + newY + " newD " + newD + " newState " + newState);
                break;
            case TrackType.turn_left:
                if (cart.d == Direction.up)
                {
                    newX--;
                    newD = Direction.left;
                }
                else if (cart.d == Direction.down)
                {
                    newX++;
                    newD = Direction.right;
                }
                else if (cart.d == Direction.right)
                {
                    newY++;
                    newD = Direction.down;
                }
                else if (cart.d == Direction.left)
                {
                    newY--;
                    newD = Direction.up;
                }
                break;
            case TrackType.turn_right:
                if (cart.d == Direction.up)
                {
                    newX++;
                    newD = Direction.right;
                }
                else if (cart.d == Direction.down)
                {
                    newX--;
                    newD = Direction.left;
                }
                else if (cart.d == Direction.right)
                {
                    newY--;
                    newD = Direction.up;
                }
                else if (cart.d == Direction.left)
                {
                    newY++;
                    newD = Direction.down;
                }
                break;
            default:
                throw new Exception("" + tile);
        }
        if (newCarts.Any(c => c.x == newX && c.y == newY))
        {
            destroyed[newCarts.Single(c => (c.x == newX && c.y == newY)).id] = true;
            Console.WriteLine($"[{newX}, {newY}]");
            Console.WriteLine(tile);
            continue;
        }
        else if (carts.Skip(index).Any(c => c.x == newX && c.y == newY))
        {
            destroyed[carts.Skip(index).Single(c => c.x == newX && c.y == newY).id] = true;
            Console.WriteLine($"[{newX}, {newY}]");
            Console.WriteLine(tile);
            continue;
        }
        index++;
        cart.x = newX;
        cart.y = newY;
        cart.d = newD;
        cart.state = newState;
        newCarts.Add(cart);
    }
    carts = new SortedSet<Cart>(comparer);
    foreach (var cart in newCarts)
    {
        if (!destroyed[cart.id])
            carts.Add(cart);
    }
    if (carts.Count() == 1)
    {
        Console.WriteLine("Last: " + carts.Single());
        return;
    }
    //if (ticks > 1000) return;
}