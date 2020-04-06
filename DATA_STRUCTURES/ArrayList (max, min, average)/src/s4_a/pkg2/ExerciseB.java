/*
 * A través de un Video resolver el siguiente problema en un código en Java o C, 
 * explicando como se hace la utilización de arreglos, la lectura/escritura, 
 * la asignación, actualización y métodos trabajados. En el video realizar 
 * la prueba de escritorio del código propuesto.
 *
 * En la Ciudad de Bogotá, se quiere llevar un registro de la cantidad de lluvia
 * que se presenta en cada uno de los doce meses del año, así como también determinar 
 * ¿En qué mes se obtuvo la mayor cantidad de lluvia?, 
 * ¿En qué mes se obtuvo la menor cantidad de lluvia?,
 * ¿Cuál es el promedio de lluvia durante el año en la Ciudad de Bogotá?
 */
package s4_a.pkg2;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

/**
 *
 * @author andre
 */
public class ExerciseB {

	public static String[] months = {
		"Enero",
		"Febrero",
		"Marzo",
		"Abril",
		"Mayo",
		"Junio",
		"Julio",
		"Agosto",
		"Septiembre",
		"Octubre",
		"Noviembre",
		"Diciembre"
	};

	public static void main(String[] args) {
		ArrayList<Rain> rains = new ArrayList<>(); // Create an ArrayList object
		for (int i = 0; i < months.length; i++) {
			String month = months[i];
			System.out.println("Ingrese cuanto llovio el mes " + month);
			double value = new Scanner(System.in).nextDouble();
			rains.add(new Rain(month, value));
		}
		Rain max = Collections.max(rains, (Rain a, Rain b) -> a.value.compareTo(b.value));
		Rain min = Collections.min(rains, (Rain a, Rain b) -> a.value.compareTo(b.value));
		double average = rains.stream().mapToDouble(a -> a.value).average().getAsDouble();
		print(getGenericMessage(max, "mayor"));
		print(getGenericMessage(min, "menor"));
		print("El promedio de lluvia durante el año en la Ciudad de Bogotá fue de: " + average);
	}

	public static String getGenericMessage(Rain rain, String text) {
		return "El mes de " + rain.month + " obtuvo la " + text + " cantidad de lluvia, siendo de " + rain.value;
	}

	public static void print(Object text) {
		System.out.println(text);;
	}
}
