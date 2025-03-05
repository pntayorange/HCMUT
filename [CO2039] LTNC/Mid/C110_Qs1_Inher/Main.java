package Paws.CO2039_LTNC.C110_Qs1_Inher;


// javac -d . Paws/CO2039_LTNC/C110_Qs1_Inher/*.java
//  java Paws.CO2039_LTNC.C110_Qs1_Inher.Main
public class Main {
    public static void main(String[] args) {
        // Create Engine instance
        Engine e = new Engine("V8", 450);
        
        // Test Engine methods
        System.out.println("Engine Type: " + e.getType()); // Expected: V8
        System.out.println("Engine Horsepower: " + e.getHorsePower()); // Expected: 450
        e.setType("V6");
        e.setHorsePower(350);
        System.out.println("Updated Engine Type: " + e.getType()); // Expected: V6
        System.out.println("Updated Engine Horsepower: " + e.getHorsePower()); // Expected: 350
        
        // Create Car instance using Engine object
        CarSub c1 = new CarSub("Ford Mustang", "F88", 800);
        
        // Test Car methods
        System.out.println("Car Model: " + c1.getModel()); // Expected: Ford Mustang
        System.out.println("Car Engine Type: " + c1.getType()); // Expected: V6
        c1.drive(); // Expected: "Car model Ford Mustang is driving"
        c1.getEngineInfo(); // Expected: "Car engine is V6 type and has 350 hp"
        
        // Create Car instance using parameters
        CarSub c2 = new CarSub("Chevrolet Camaro", "V8", 500);
        
        // Test Car methods for second object
        System.out.println("Car Model: " + c2.getModel()); // Expected: Chevrolet Camaro
        System.out.println("Car Engine Type: " + c2.getType()); // Expected: V8
        c2.drive(); // Expected: "Car model Chevrolet Camaro is driving"
        c2.getEngineInfo(); // Expected: "Car engine is V8 type and has 500 hp"
        
        // Test setting new engine
        c2.setEngine(e); // Setting V6 engine
        System.out.println("Updated Car Engine Type: " + c2.getType()); // Expected: V6
    }
}
