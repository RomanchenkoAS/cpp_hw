# Какое то задание не по уровню, как будто бы от первой части курса, плюс меня терзают подозрения что вы уже не читаете мои домашки
# что бы подтвердить свои подозрения я сдам эту на питончике :)


def main() -> None:
    initial_list = [1, 2, 3, 20, 99, 20, 100]

    # Задача 1
    # Дан список некоторых целых чисел, найдите значение 20 в нем и, если оно присутствует, замените его на 200. Обновите список только при первом вхождении числа 20.
    list = initial_list
    print(f"\nTask #1\nInitial list: {list}")
    if 20 in list:
        list[list.index(20)] = 200
    print(f"List with 20 substituted by 200: {list}\n")

    # Задача 2
    # Необходимо удалить пустые строки из списка строк.
    list = ["Hello", ",", "", "world", "", "!", ""]
    print(f"\nTask #2\nInitial list:")
    for position, string in enumerate(list):
        print(position, string)

    print(f"Resulting list:")
    for position, string in enumerate(
        [string for string in list if string != ""]
    ):
        print(position, string)

    # Задача 3
    # Дан список чисел. Превратите его в список квадратов этих чисел.
    list = initial_list
    print(f"\nTask #3\nInitial list: {list}")
    print(f"Resulting list: {[i*i for i in list]}")

    # Задача 4
    # Дан список чисел, необходимо удалить все вхождения числа 20 из него.
    list = initial_list
    print(f"\nTask #4\nInitial list: {list}")
    print(f"Resulting list: {[i for i in list if i != 20]}")

    # Задача 5
    # Необходимо вывести список в обратном порядке.
    list = initial_list
    print(f"\nTask #5\nInitial list: {list}")
    print(f"Resulting list: {list[::-1]}")


if __name__ == "__main__":
    main()
