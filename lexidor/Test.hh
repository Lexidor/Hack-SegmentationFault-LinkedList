<?hh // strict

<<__EntryPoint>>
function main_test(): void {
    require_once __DIR__.'/../vendor/autoload.hack';
    Facebook\AutoloadMap\initialize();
    $list = new LinkedList(range(0, 1000000));
    $list->__toString();
    foreach ($list->toGenerator() as $key => $val) {
        printf("(%d, %d)\n", $key, $val);
    }
}
