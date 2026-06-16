def main():
    print("Hello from day13!")


class Person:
    count_person = 0

    def __init__(self, name):
        self.name = name
        Person.count_person += 1


class Student(Person):
    def __init__(self, name):
        super().__init__(name)

    def say(self):
        print(f"I'm {self.name}")

    @classmethod
    def is_in_school(cls):
        print("We're in school now")


if __name__ == "__main__":
    main()
    xiaoming = Student("小明")
    xiaoming.say()
