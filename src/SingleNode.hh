<?hh // strict

class SingleNode<T> {

    public function __construct(
        private T $value,
        private ?SingleNode<T> $next = null,
    ) {}

    public function append(SingleNode<T> $next): this {
        $this->next = $next;
        return $this;
    }

    public function getNext(): ?SingleNode<T> {
        return $this->next;
    }

    public function getValue(): T {
        return $this->value;
    }
}
