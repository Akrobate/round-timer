
/**
 * test method
 * @returns {Promise<Array>}
 */
async function getBusinessState() {
    try {
        const result = await fetch('/api/business-state',
            {
                method: 'GET',
            }
        )
        return result.json()
    } catch (error) {
        console.log('serverGet - Error:', error)
        return []
    }
}
