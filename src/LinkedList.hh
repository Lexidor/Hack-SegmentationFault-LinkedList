<?hh // strict

use HH\Lib\Vec;
use HH\Lib\C;
use HH\Lib\Str;

class LinkedList<T> {

    /** @var May be the $headTail, for real head see getRealHead()*/
    private SingleNode<T> $head;
    /** @var May be the $headTail, for real head see getRealTail()*/
    private SingleNode<T> $tail;

    <<TimeComplexity('O(N)')>>
    public function __construct(Traversable<T> $values = vec[]) {
        $headTail = new SingleNode('DONT_CARE');
        /*HH_IGNORE_ERROR[4110] Requires default(T)*/
        $this->head = $headTail;
        /*HH_IGNORE_ERROR[4110] Requires default(T)*/
        $this->tail = $headTail;
        $this->appendRange($values);
    }

    <<TimeComplexity('O(1)')>>
    public function append(T $value): void {
        $end = new SingleNode($value);
        $this->tail->append($end);
        $this->tail = $end;
    }

    <<TimeComplexity('O(N)')>>
    public function appendRange(Traversable<T> $values): void {
        $nodes = Vec\map($values, $val ==> new SingleNode($val));

        $prev = $this->tail;
        foreach ($nodes as $node) {
            $prev->append($node);
            $prev = $node;
        }
        $this->tail = $prev;
    }

    <<TimeComplexity('O(N)')>>
    public function toGenerator(): Generator<int, T, void> {
        $node = $this->head;
        $ii = 0;
        while (($node = $node->getNext()) !== null) {
            yield $ii => $node->getValue();
            $ii++;
        }
    }

    <<TimeComplexity('O(N)')>>
    public function toVec(): vec<T> {
        $out = vec[];
        $node = $this->head;
        while (($node = $node->getNext()) !== null) {
            $out[] = $node->getValue();
        }
        return $out;
    }

    <<TimeComplexity('O(1)')>>
    public function first(): ?T {
        return $this->getRealTail()?->getValue();
    }

    <<TimeComplexity('O(1)')>>
    public function last(): ?T {
        return $this->getRealTail()?->getValue();
    }

    <<TimeComplexity('O(N)')>>
    public function count(): int {
        return C\count($this->toVec());
    }

    /**
     * You can only use __toString() if T is (arraykey|float|bool|Stringish)
     * hackfmt-ignore
     */
    <<TimeComplexity('O(N*f) where f is the complexity of a string cast on type T')>>
    public function __toString(): string {
        return print_r($this->toVec(), true);
    }

    /**
     * Prevents from reading the $headTail value.
     */
    <<TimeComplexity('O(1)')>>
    private function getRealHead(): ?SingleNode<T> {
        return $this->head === $this->tail ? null : $this->head;
    }

    /**
     * Prevents from reading the $headTail value.
     */
    <<TimeComplexity('O(1)')>>
    private function getRealTail(): ?SingleNode<T> {
        return $this->head === $this->tail ? null : $this->tail;
    }

}
