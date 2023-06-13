import { Request, Response, Router } from "express";

const routes = Router();
const CONSENSUS_THRESHOLD = 2;

// Store results from different endpoints
const resultsCache: {
  fibonacci: Map<number, number>;
  factorial: Map<number, number>;
} = {
  fibonacci: new Map(),
  factorial: new Map(),
};

routes.post("/fibonacci", (req: Request, res: Response) => {
  const fibonacciResult: number = req.body.result;

  // Save Fibonacci data to cache
  if (resultsCache.fibonacci.get(fibonacciResult))
    resultsCache.fibonacci.set(
      fibonacciResult,
      resultsCache.fibonacci.get(fibonacciResult) + 1
    );
  else resultsCache.fibonacci.set(fibonacciResult, 1);

  let hasDecisiveVote = false;
  let result: number = null;

  for (const [key, value] of resultsCache.fibonacci) {
    if (value >= CONSENSUS_THRESHOLD) {
      hasDecisiveVote = true;
      result = key;
      break;
    }
  }

  if (hasDecisiveVote) {
    resultsCache.fibonacci.clear();

    console.log(`Most voted result for fibonacci: ${result}`);

    return res.json({ result: result });
  } else {
    return res.json({ result: "Waiting for more results sent to /fibonacci" });
  }
});

routes.post("/factorial", (req: Request, res: Response) => {
  const factorialResult: number = req.body.result;

  // Save Fibonacci data to cache
  if (resultsCache.factorial.get(factorialResult))
    resultsCache.factorial.set(
      factorialResult,
      resultsCache.factorial.get(factorialResult) + 1
    );
  else resultsCache.factorial.set(factorialResult, 1);

  let hasDecisiveVote = false;
  let result: number = null;

  for (const [key, value] of resultsCache.factorial) {
    if (value >= CONSENSUS_THRESHOLD) {
      hasDecisiveVote = true;
      result = key;
      break;
    }
  }

  if (hasDecisiveVote) {
    resultsCache.factorial.clear();

    console.log(`Most voted result for factorial: ${result}`);

    return res.json({ result: result });
  } else {
    return res.json({ result: "Waiting for more results sent to /factorial" });
  }
});

export default routes;
