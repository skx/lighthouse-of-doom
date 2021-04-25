// TODO:
//
// 1. Inventory Management
//  [x]has_item(name);
//  [x]take_item("name")
//  [x]drop_item("name");
//    We want to add "inventory" which will use these.
//    get torch|mirror|telephone will work too
//    we need to have the torch for the basement
//
// 2. [x] BUG "TAKE RUG", and "TAKE TORCH" don't test if the item is present.
//
// 3. [x] The telephone should do something
//
// 4. [x] Going in the basement should kill you without the torch.
//
// 5. [x] The game is not winnable.
//
// 6. [x] Allow the torch to be turned on and off
//        "USE TORCH" will turn it into a lit torch.
//
// 7. [x] Allow "USE TORCH" while in basement.
//
// 8. [x] Examine should show the `edesc` attribute from an object
//
// 9. [x] Items should be invisible - i.e. present but not shown in the room
//        e.g. Painting, Desk.
//
// 10. [ ] "OPEN" is the last of our handlers with hardcoded behaviour
//         (If we ignore "UP" and "DOWN").
//
// 11. [ ] GO UP | GO DOWN should be synonyms
//
//
// Additions:
//
//   Allow the trapdoor to be closed
//     If the trapdoor is opened the grue might escape?
//


// Add a dog
//
//  EXAMINE DOG
//  -> "The dog is asleep, and as you disturbed him he mutters something"
//     "about 'Apollo the Super-pup', and settles back into a comfortable dream"
//
