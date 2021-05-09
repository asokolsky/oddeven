import itertools
from typing import Optional, List, Tuple, Union


def packA( elts: List[int]) -> Optional[ List[int]]:
    '''
    Given the list of item weights pick such that:
    1. Total weights of these is more than 1/2 of the total
    2. length of the result is minimal
    3. Result is sorted in the increasing weight
    4. If more than one result exists pick the one with larger total weight

    If all fails, return None
    '''
    def totalWeight( elts: Union[List[int], Tuple[int]] ) -> Optional[int]:
        return sum( elts )
        #res = None
        #for res in itertools.accumulate( elts ):
        #    pass
        #return res

    #print( 'packA', elts )
    assert isinstance( elts, list )

    w = totalWeight( elts )
    targetWeight = w / 2
    #print( 'totalWeight:', w, 'targetWeight:', targetWeight )

    for l in range( 1, len(elts) + 1 ):
        # iterate over all the subsets of length l of the list elts
        ress: List[ Tuple[ int ] ] = []
        for c in  itertools.combinations( elts, l ):
            if totalWeight( c ) > targetWeight:
                ress.append( c )
        if not ress:
            continue

        # find the result with the biggest weight
        #print( 'ress:', ress )
        res = max( ress, key=totalWeight )
        #print( 'res:', res )
        res = sorted( res )
        print( 'packA', elts, '=>', res )
        return res

    return None

if __name__ == '__main__':
    assert packA( [3, 7, 5, 6, 2] ) == [6, 7]
    assert packA( [5, 3, 2, 4, 1, 2] ) == [4, 5]
    assert packA( [4, 2, 5, 1, 6] ) == [5, 6]
