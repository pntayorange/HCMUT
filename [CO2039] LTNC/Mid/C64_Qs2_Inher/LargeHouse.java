package Paws.CO2039_LTNC.Inher;

import java.util.ArrayList;
import java.util.List;

public class LargeHouse extends Room{
    private List<Room> subrooms;

    public LargeHouse(String name, double area) {
        super(name, area);
        this.subrooms = new ArrayList<Room>();
    }
    public void addSubRoom(Room room) {
        this.subrooms.add(room);
    }
    public Room getSubRoom(int index) {
        return this.subrooms.get(index);
    }

    public double getTotalArea() {
        double totalArea = this.getArea();
        for (Room room : subrooms) {
            totalArea += room.getArea();
        }
        return totalArea;
    }
}