package Paws.CO2039_LTNC.House;

import java.util.ArrayList;
import java.util.List;

public class House {
    private String address;
    private List<Room> rooms;

    public House(String address) {
        this.address = address;
        this.rooms = new ArrayList<Room>();
    }
    public String getAddress() {
        return this.address;
    }
    public void setAddress(String address) {
        this.address = address;
    }
    public void addRoom(Room room) {
        this.rooms.add(room);
    }

    public Room getRoom(int index){
        return this.rooms.get(index);
    }
    public double getTotalArea(){
        double totalArea = 0;
        for (Room room : rooms) {
            totalArea += room.getArea();
        }
        return totalArea;
    }
}
